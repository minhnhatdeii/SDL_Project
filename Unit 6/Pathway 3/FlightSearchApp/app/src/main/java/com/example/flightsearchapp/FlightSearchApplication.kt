package com.example.flightsearchapp

import android.app.Application
import android.content.Context
import androidx.datastore.core.DataStore
import androidx.datastore.preferences.core.Preferences
import androidx.datastore.preferences.preferencesDataStore
import com.example.flightsearchapp.data.AppContainer
import com.example.flightsearchapp.data.AppDataContainer
import com.example.flightsearchapp.data.SearchBarRepository

private const val SEARCH_PREFERENCE_NAME = "search_preferences"
private val Context.dataStore: DataStore<Preferences> by preferencesDataStore(
    name = SEARCH_PREFERENCE_NAME
)

class FlightSearchApplication : Application() {
    lateinit var container: AppContainer
    lateinit var searchBarRepository: SearchBarRepository

    override fun onCreate() {
        super.onCreate()
        container = AppDataContainer(this)
        searchBarRepository = SearchBarRepository(dataStore)
    }
}
