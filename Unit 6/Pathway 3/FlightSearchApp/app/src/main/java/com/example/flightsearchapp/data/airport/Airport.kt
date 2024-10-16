package com.example.flightsearchapp.data.airport

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "airport")
data class Airport (
    @PrimaryKey
    val id: Int,
    val name: String,
    @ColumnInfo(name = "iata_code")
    val iataCode: String,
    val passengers: Int
)

@Entity(tableName = "favorite")
data class Favorite (
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0,
    @ColumnInfo(name = "departure_code")
    val departureCode: String,
    @ColumnInfo(name = "destination_code")
    val destinationCode: String
)

data class Flight(
    val departure: Airport,
    val destination: Airport,
    var favorite: Boolean = false
)