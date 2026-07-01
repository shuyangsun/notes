package com.shuyangsun.notes.ktinaction.ch02.sec2

class Rectangle(val height: UInt, val width: UInt) {
    val hasArea = height > 0u && width > 0u

    val isSquare: Boolean
        get() = hasArea && height == width
}
