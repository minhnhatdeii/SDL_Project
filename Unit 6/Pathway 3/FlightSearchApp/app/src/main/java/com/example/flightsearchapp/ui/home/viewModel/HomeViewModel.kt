package com.example.flightsearchapp.ui.home.viewModel

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.flightsearchapp.data.SearchBarRepository
import com.example.flightsearchapp.data.airport.Airport
import com.example.flightsearchapp.data.airport.AirportRepository
import com.example.flightsearchapp.data.airport.Favorite
import com.example.flightsearchapp.data.airport.Flight
import kotlinx.coroutines.FlowPreview
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.flow.debounce
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.flow.firstOrNull
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import java.util.concurrent.atomic.AtomicBoolean

class HomeViewModel(
    private val getSearchResults: GetSearchResults,
    private val airportRepository: AirportRepository,
    private val searchBarRepository: SearchBarRepository
) : ViewModel() {

    sealed interface HomeUiState {
        data class IdleScreen(val favoritesList: MutableList<Flight>) : HomeUiState
        object Loading : HomeUiState
        object Error : HomeUiState
        object NoResults : HomeUiState
        data class SearchResultsFetched(val airports: Flow<List<Airport>>) : HomeUiState
        data class SearchResultClicked(
            val departingAirport: Airport,
            val flightsList: List<Flight> = emptyList()
        ) : HomeUiState
    }

    sealed interface SearchFieldState {
        object Idle : SearchFieldState //bezczynny
        object EmptyActive : SearchFieldState
        object WithInputActive : SearchFieldState
    }


    private val _searchFieldState: MutableStateFlow<SearchFieldState> =
        MutableStateFlow(SearchFieldState.Idle)
    val searchFieldState: StateFlow<SearchFieldState> = _searchFieldState

    private val _homeUiState: MutableStateFlow<HomeUiState> =
        MutableStateFlow(HomeUiState.IdleScreen(mutableListOf()))

    private suspend fun getFavoriteFlights() {
        airportRepository.getFavoriteFlights().collect { favorites ->
            val favoritesList: MutableList<Flight> = mutableListOf()
            for (favorite in favorites) {
                // get flight information from the iata codes
                val origin: Airport? =
                    airportRepository.getAirportByIataCode(favorite.departureCode).firstOrNull()
                val destination: Airport? =
                    airportRepository.getAirportByIataCode(favorite.destinationCode).firstOrNull()
                // add to favorites as long as both airports were found
                if (origin != null && destination != null)
                    favoritesList.add(
                        Flight(
                            departure = origin,
                            destination = destination,
                            favorite = true
                        )
                    )
            }
            _homeUiState.update {
                HomeUiState.IdleScreen(favoritesList = favoritesList)
            }
        }
    }

    val homeUiState: StateFlow<HomeUiState> = _homeUiState

    private val _inputText: MutableStateFlow<String> = MutableStateFlow("")
    val inputText: StateFlow<String> = _inputText

    private val isInitialized = AtomicBoolean(false)

    @OptIn(FlowPreview::class)
    fun initialize() {
        if (isInitialized.compareAndSet(false, true)) {
            viewModelScope.launch {
                loadSearchQuery()
                inputText.debounce(timeoutMillis = TIMEOUT_MILLIS).collectLatest { input ->
                    if (input.blankOrEmpty()) {
                        getFavoriteFlights()
                        return@collectLatest
                    }
                    when (val result = getSearchResults(input)) {
                        is GetSearchResults.Result.Success -> {
                            _homeUiState.update { HomeUiState.SearchResultsFetched(result.airports) }
                            // Check for empty results after emitting SearchResultsFetched
                            result.airports.collect { airports ->
                                if (airports.isEmpty()) {
                                    _homeUiState.update { HomeUiState.NoResults }
                                }
                            }
                        }

                        is GetSearchResults.Result.Error -> {
                            _homeUiState.update { HomeUiState.Error }
                        }
                    }
                }
            }
        }
    }

    fun updateInput(inputText: String) {
        _inputText.update { inputText }
        viewModelScope.launch {
            searchBarRepository.saveSearchQueryToDataStore(inputText)
        }
        activateSearchField()

        if (inputText.blankOrEmpty().not()) {
            _homeUiState.update { HomeUiState.Loading }
        }
    }

    fun searchFieldActivated() {
        activateSearchField()
    }

    fun revertToInitialState() {
        _inputText.update { "" }
        _searchFieldState.update { SearchFieldState.Idle }
    }

    fun clearInput() {
        _inputText.update { "" }
        _searchFieldState.update { SearchFieldState.EmptyActive }
    }

    private fun activateSearchField() {
        if (inputText.value.blankOrEmpty().not()) {
            _searchFieldState.update { SearchFieldState.WithInputActive }
        } else {
            _searchFieldState.update { SearchFieldState.EmptyActive }
        }
    }

    fun onItemClicked(departingAirport: Airport) {
        viewModelScope.launch {
            airportRepository.getDestinationAirports(departingAirport.name).collect { airports ->
                val flightsList: MutableList<Flight> = mutableListOf()
                for (airport in airports) {
                    if (getFavorite(departingAirport.iataCode, airport.iataCode) == null)
                        flightsList.add(Flight(departingAirport, airport))
                    else
                        flightsList.add(Flight(departingAirport, airport, favorite = true))
                }
                // Update UI state with a list of all valid flights
                _homeUiState.update {
                    HomeUiState.SearchResultClicked(
                        departingAirport = departingAirport,
                        flightsList = flightsList
                    )
                }
            }
        }
    }

    fun onFavoriteClicked(flight: Flight) {
        viewModelScope.launch {
            val favorite = getFavorite(flight.departure.iataCode, flight.destination.iataCode)
            Log.d("Favorite", "onFavoriteClicked: $favorite")
            if (favorite == null) {
                flight.favorite = true
                airportRepository.insertFavorite(
                    Favorite(
                        departureCode = flight.departure.iataCode,
                        destinationCode = flight.destination.iataCode
                    )
                )
            } else {
                airportRepository.deleteFavorite(favorite)
                flight.favorite = false
            }
            Log.d("Favorite", "Flight Favorite: ${flight.favorite}")
        }
    }

    private suspend fun getFavorite(departureCode: String, destinationCode: String): Favorite? {
        return airportRepository.getFavoriteByIataCode(
            departureCode = departureCode,
            destinationCode = destinationCode
        ).firstOrNull()
    }

    private suspend fun loadSearchQuery() {
        val searchQuery = searchBarRepository.searchQuery.first()
        Log.d("SearchBar", "loadSearchQuery: $searchQuery")
        _inputText.update { searchQuery }

        if (searchQuery.isNotBlank()) {
            // Update UI state based on loaded query
            _homeUiState.update { HomeUiState.Loading } // Or a more appropriate state
            // Trigger search or data loading based on searchQuery
            // ... (e.g., call getSearchResults(searchQuery)) ...
        }
    }

    private fun String.blankOrEmpty() = this.isBlank() || this.isEmpty()

    companion object {
        private const val TIMEOUT_MILLIS = 5_00L
    }
}
