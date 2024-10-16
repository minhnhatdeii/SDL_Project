package com.example.flightsearchapp.ui.home.viewModel

import com.example.flightsearchapp.data.airport.Airport
import com.example.flightsearchapp.data.airport.AirportRepository
import kotlinx.coroutines.flow.Flow
import java.io.IOException

class GetSearchResults(private val airportRepository: AirportRepository) {

    sealed interface Result {
        object Error : Result
        data class Success(val airports: Flow<List<Airport>>) : Result
    }

    operator fun invoke(searchTerm: String): Result = try {
        val airports = airportRepository.getAllAirports(searchTerm)
        Result.Success(airports = airports)
    } catch (e: IOException) {
        Result.Error
    }
}