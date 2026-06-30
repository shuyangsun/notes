package com.shuyangsun.notes.ktinaction.ch02

import com.shuyangsun.notes.ktinaction.ch02.sec1.*
import com.shuyangsun.notes.ktinaction.ch02.sec2.*
import com.shuyangsun.notes.ktinaction.ch02.sec3.*

fun main() {
    runSection1()
    runSection2()
    runSection3()
}

fun printSec(sec: Int, newline: Boolean = true) =
    println("${if (newline) "\n" else ""}Section $sec:")

fun runSection1() {
    printSec(1, newline = false)
    val a = 3
    val b = 5
    println("The maximum value between $a and $b is ${max(3, 5)}.")
}

fun runSection2() {
    printSec(2)
    val person = Person("Shuyang", false)
    person.isStudent = true
    println("$person")

    println()

    val rect1 = Rectangle(3u, 5u)
    val rect2 = Rectangle(0u, 2u)
    println("rect1 is ${if (rect1.isSquare) "" else "not "}square.")
    if (!rect2.hasArea) {
        println("rect2 does not have an area.")
    }
}

fun runSection3() {
    printSec(3)
    val color = Color.RED
    color.printColor()
    println("$color's mnemonic is \"${getMnemonic(color)}\", it is ${getWarmth(color)}.")

    val c1 = Color.RED
    val c2 = Color.YELLOW
    val c3 = Color.BLUE
    println("The mix of $c1 and $c2 is ${mixOptimized(c1, c2).getOrNull()}.")
    println("The mix of $c1 and $c3 is ${mix(c1, c3).getOrNull()}.")

    println()

    val a = Num(3)
    val b = Num(5)
    val c = Num(2)
    val expr1 = Sum(a, b)
    println("expr1 = $expr1")
    println("The sum of $a, $b, and $c is ${eval(Sum(expr1, c)).getOrThrow()}.")

    println()

    for (i in 1..3) {
        print("$i, ")
    }
    println()
    for (i in 1..<5) {
        print("$i, ")
    }
    println()
    for (i in 10 downTo 1 step 3) {
        print("$i, ")
    }
    println()

    println()

    for ((lang, compiled) in langToCompiled) {
        println("$lang is ${if (compiled) "" else "NOT"} a compiled language.")
    }
}
