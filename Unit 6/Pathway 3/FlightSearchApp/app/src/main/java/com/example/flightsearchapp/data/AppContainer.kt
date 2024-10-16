package com.example.flightsearchapp.data

import android.content.Context
import com.example.flightsearchapp.data.airport.AirportRepository

interface AppContainer {
    val airportRepository: AirportRepository
}

class AppDataContainer(private val context: Context) : AppContainer {
    override val airportRepository: AirportRepository by lazy {
        AirportRepository(FlightSearchDatabase.getDatabase(context).airportDao())
    }
}
