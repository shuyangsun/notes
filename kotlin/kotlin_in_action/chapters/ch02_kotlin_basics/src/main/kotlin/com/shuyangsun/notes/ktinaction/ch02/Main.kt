package com.shuyangsun.notes.ktinaction.ch02

import com.shuyangsun.notes.ktinaction.ch02.sec1.max
import com.shuyangsun.notes.ktinaction.ch02.sec2.Person
import com.shuyangsun.notes.ktinaction.ch02.sec2.Rectangle

fun main() {
  runSection1()
  runSection2()
}

fun runSection1() {
  val a = 3
  val b = 5
  println("The maximum value between $a and $b is ${max(3, 5)}.")
}

fun runSection2() {
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
