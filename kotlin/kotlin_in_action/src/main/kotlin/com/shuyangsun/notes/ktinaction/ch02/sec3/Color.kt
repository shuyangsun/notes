package com.shuyangsun.notes.ktinaction.ch02.sec3

enum class Color(
    val r: Int,
    val g: Int,
    val b: Int,
) {
    RED(255, 0, 0),
    ORANGE(255, 165, 0),
    YELLOW(255, 255, 0),
    GREEN(0, 255, 0),
    BLUE(0, 0, 255),
    INDIGO(75, 0, 130),
    VIOLET(238, 130, 238);

    val rgb = (r * 256 + g) * 256 + b

    fun printColor() = println("$this is $rgb")
}

fun getMnemonic(color: Color) =
    when (color) {
        Color.RED -> "Richard"
        Color.ORANGE -> "Of"
        Color.YELLOW -> "York"
        Color.GREEN -> "Gave"
        Color.BLUE -> "Battle"
        Color.INDIGO -> "In"
        Color.VIOLET -> "Vain"
    }

enum class ColorWarmth {
    WARM,
    NEUTRAL,
    COLD,
}

fun getWarmth(color: Color) =
    when (color) {
        Color.RED,
        Color.ORANGE,
        Color.YELLOW -> ColorWarmth.WARM
        Color.GREEN -> ColorWarmth.NEUTRAL
        Color.BLUE,
        Color.INDIGO,
        Color.VIOLET -> ColorWarmth.COLD
    }

fun mix(c1: Color, c2: Color) =
    when (setOf(c1, c2)) {
        setOf(Color.RED, Color.YELLOW) -> Result.success(Color.ORANGE)
        setOf(Color.YELLOW, Color.BLUE) -> Result.success(Color.GREEN)
        setOf(Color.BLUE, Color.VIOLET) -> Result.success(Color.INDIGO)
        else -> Result.failure(Exception("Dirty color"))
    }

private fun checkColor(c1: Color, c2: Color, c1c: Color, c2c: Color) =
    (c1 == c1c && c2 == c2c) || (c2 == c1c && c1 == c2c)

fun mixOptimized(c1: Color, c2: Color) =
    when {
        checkColor(c1, c2, Color.RED, Color.YELLOW) -> Result.success(Color.ORANGE)
        checkColor(c1, c2, Color.YELLOW, Color.BLUE) -> Result.success(Color.GREEN)
        checkColor(c1, c2, Color.BLUE, Color.VIOLET) -> Result.success(Color.INDIGO)
        else -> Result.failure(Exception("Dirty color"))
    }
