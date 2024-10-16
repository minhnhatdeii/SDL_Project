package com.example.flightsearchapp.data.airport

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface AirportDao {
    @Query("SELECT * FROM airport WHERE iata_code LIKE '%' || :inputText || '%' OR name LIKE '%' || :inputText || '%'")
    fun getAllAirports(inputText: String): Flow<List<Airport>>

    @Query("SELECT * FROM airport WHERE iata_code = :iataCode LIMIT 1")
    fun getAirportByIataCode(iataCode: String): Flow<Airport>

    @Query("SELECT * FROM favorite")
    fun getFavoriteFlights(): Flow<List<Favorite>>

    @Insert(onConflict = OnConflictStrategy.IGNORE)
    suspend fun insertFavorite(favorite: Favorite)

    @Delete
    suspend fun deleteFavorite(favorite: Favorite)

    @Query("SELECT * FROM favorite WHERE departure_code = :departureCode AND destination_code = :destinationCode")
    fun getFavoriteByIataCode(departureCode: String, destinationCode: String): Flow<Favorite>

    @Query("""
        SELECT * FROM airport
        WHERE name NOT LIKE :departingAirport
    """)
    fun getDestinationAirports(departingAirport: String): Flow<List<Airport>>
}
