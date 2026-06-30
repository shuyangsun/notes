package com.shuyangsun.notes.ktinaction.ch02

import com.shuyangsun.notes.ktinaction.ch02.sec1.max
import com.shuyangsun.notes.ktinaction.ch02.sec2.Person

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
}
