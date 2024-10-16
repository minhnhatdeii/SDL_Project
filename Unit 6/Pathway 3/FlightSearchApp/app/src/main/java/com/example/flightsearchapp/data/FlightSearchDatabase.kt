package com.example.flightsearchapp.data

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase
import com.example.flightsearchapp.data.airport.Airport
import com.example.flightsearchapp.data.airport.AirportDao
import com.example.flightsearchapp.data.airport.Favorite

@Database(entities = [Airport::class, Favorite::class], version = 2, exportSchema = false)
abstract class FlightSearchDatabase : RoomDatabase() {

    abstract fun airportDao(): AirportDao

    companion object {
        @Volatile
        private var Instance: FlightSearchDatabase? = null
        fun getDatabase(context: Context): FlightSearchDatabase {
            return Instance ?: synchronized(this) {
                val MIGRATION_1_2 = object : Migration(1, 2) {
                    override fun migrate(database: SupportSQLiteDatabase) {
                        database.execSQL(
                            """
            CREATE TABLE IF NOT EXISTS `favorite` (
                `id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
                `departure_code` TEXT NOT NULL,
                `destination_code` TEXT NOT NULL
            )
            """
                        )
                    }
                }
                Room.databaseBuilder(
                    context,
                    FlightSearchDatabase::class.java,
                    "flight_search_database"
                )
                    .createFromAsset("flight_search.db")
                    .addMigrations(MIGRATION_1_2)
                    .build()
                    .also { Instance = it }
            }
        }
    }


}
