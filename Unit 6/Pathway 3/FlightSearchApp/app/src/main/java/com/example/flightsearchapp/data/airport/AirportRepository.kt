package com.example.flightsearchapp.data.airport

import kotlinx.coroutines.flow.Flow

class AirportRepository(private val airportDao: AirportDao) {
    fun getAllAirports(searchTerm: String): Flow<List<Airport>> =
        airportDao.getAllAirports(searchTerm)

    fun getAirportByIataCode(iataCode: String): Flow<Airport> =
        airportDao.getAirportByIataCode(iataCode)

    fun getFavoriteFlights(): Flow<List<Favorite>> = airportDao.getFavoriteFlights()
    suspend fun insertFavorite(favorite: Favorite) =
        airportDao.insertFavorite(favorite)

    suspend fun deleteFavorite(favorite: Favorite) = airportDao.deleteFavorite(favorite)
    fun getFavoriteByIataCode(departureCode: String, destinationCode: String): Flow<Favorite> =
        airportDao.getFavoriteByIataCode(departureCode, destinationCode)

    fun getDestinationAirports(departingAirport: String): Flow<List<Airport>> = airportDao.getDestinationAirports(departingAirport)
}
