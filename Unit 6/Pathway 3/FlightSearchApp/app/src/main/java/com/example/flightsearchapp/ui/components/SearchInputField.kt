package com.example.flightsearchapp.ui.components

import androidx.compose.foundation.border
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.foundation.interaction.PressInteraction
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.KeyboardArrowRight
import androidx.compose.material.icons.filled.Close
import androidx.compose.material.icons.filled.Search
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldColors
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.flightsearchapp.R
import com.example.flightsearchapp.ui.home.viewModel.HomeViewModel
import com.example.flightsearchapp.ui.theme.color_silver
import com.example.flightsearchapp.ui.theme.color_soft_silver

enum class IconType {
    Search, Clear, Chevron
}

@Composable
fun SearchInputField(
    searchFieldState: HomeViewModel.SearchFieldState,
    inputText: String,
    onSearchInputChanged: (String) -> Unit,
    onClearInputClicked: () -> Unit,
    onClicked: () -> Unit,
    onChevronClicked: () -> Unit,
) {
    TextField(
        modifier = Modifier
            .fillMaxWidth()
            .padding(start = 12.dp, top = 8.dp, end = 12.dp)
            .border(width = 1.dp, color = color_silver, shape = RoundedCornerShape(32.dp)),
        value = inputText,
        onValueChange = { newText -> onSearchInputChanged(newText) },
        singleLine = true,
        keyboardOptions = KeyboardOptions.Default.copy(imeAction = ImeAction.Done),
        shape = RoundedCornerShape(32.dp),
        colors = AppTextInputColors,
        leadingIcon = {
            when (searchFieldState) {
                HomeViewModel.SearchFieldState.Idle -> SearchIcon(IconType.Search)
                HomeViewModel.SearchFieldState.EmptyActive,
                HomeViewModel.SearchFieldState.WithInputActive -> SearchIcon(
                    IconType.Chevron,
                    onChevronClicked
                )
            }
        },
        trailingIcon = {
            if (searchFieldState is HomeViewModel.SearchFieldState.WithInputActive) {
                SearchIcon(IconType.Clear, onClearInputClicked)
            }
        },
        placeholder = {
            Text(
                text = "What are you searching for?",
            )
        },
        interactionSource = remember { MutableInteractionSource() }.also { interactionSource ->
            LaunchedEffect(key1 = interactionSource) {
                interactionSource.interactions.collect { interaction ->
                    if (interaction is PressInteraction.Release) {
                        onClicked.invoke()
                    }
                }
            }
        },
    )
}


@Composable
fun SearchIcon(iconType: IconType, onClick: (() -> Unit)? = null) {
    val imageVector = when (iconType) {
        IconType.Search -> Icons.Filled.Search
        IconType.Clear -> Icons.Filled.Close
        IconType.Chevron -> Icons.AutoMirrored.Filled.KeyboardArrowRight
    }
    val contentDescription = when (iconType) {
        IconType.Search -> stringResource(id = R.string.search)
        IconType.Clear -> stringResource(id = R.string.close)
        IconType.Chevron -> stringResource(id = R.string.chevron)
    }

    IconButton(onClick = onClick ?: {}) { // Use empty lambda if onClick is null
        Icon(imageVector = imageVector, contentDescription = contentDescription)
    }
}


@Preview(showBackground = true)
@Composable
fun SearchInputFieldPreview(uiState: HomeViewModel.SearchFieldState = HomeViewModel.SearchFieldState.Idle) {
    SearchInputField(uiState, "Text", {}, {}, {}, {})
}

private val AppTextInputColors: TextFieldColors
    @Composable
    get() = OutlinedTextFieldDefaults.colors(
        focusedContainerColor = color_soft_silver,
        unfocusedContainerColor = color_soft_silver,
        focusedBorderColor = Color.Transparent,
        unfocusedBorderColor = Color.Transparent,
    )