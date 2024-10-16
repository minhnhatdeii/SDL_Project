package com.example.flightsearchapp.ui

import androidx.lifecycle.ViewModelProvider.AndroidViewModelFactory.Companion.APPLICATION_KEY
import androidx.lifecycle.viewmodel.CreationExtras
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.flightsearchapp.FlightSearchApplication
import com.example.flightsearchapp.ui.home.viewModel.GetSearchResults
import com.example.flightsearchapp.ui.home.viewModel.HomeViewModel

object AppViewModelProvider {
    val Factory = viewModelFactory {
        initializer {
            HomeViewModel(
                GetSearchResults(flightSearchApplication().container.airportRepository),
                flightSearchApplication().container.airportRepository,
                flightSearchApplication().searchBarRepository
            )
        }
    }
}

fun CreationExtras.flightSearchApplication(): FlightSearchApplication =
    (this[APPLICATION_KEY] as FlightSearchApplication)