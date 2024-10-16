package com.example.flightsearchapp.ui.home.screens

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import com.example.flightsearchapp.data.airport.Airport

@Composable
fun SuggestionsBody(
    airports: List<Airport>,
    modifier: Modifier,
    onItemClicked: (Airport) -> Unit
) {
    LazyColumn(
        verticalArrangement = Arrangement.spacedBy(12.dp),
        modifier = modifier
    ) {
        items(items = airports, key = { it.id }) { airport ->
            AirportRow(
                airport = airport,
                onItemClicked = onItemClicked
            )
        }
    }
}

@Composable
fun AirportRow(airport: Airport, onItemClicked: (Airport) -> Unit) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .clickable { onItemClicked(airport) }
    ) {

        Text(
            text = airport.iataCode,
            style = MaterialTheme.typography.titleSmall,
            fontWeight = FontWeight.Bold,
            textAlign = TextAlign.Center,
            modifier = Modifier
                .width(50.dp)
        )
        Text(
            text = airport.name,
            style = MaterialTheme.typography.bodyMedium
        )
    }
}