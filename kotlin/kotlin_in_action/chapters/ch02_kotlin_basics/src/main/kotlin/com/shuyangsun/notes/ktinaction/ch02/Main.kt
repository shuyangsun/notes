package com.shuyangsun.notes.ktinaction.ch02

import com.shuyangsun.notes.ktinaction.ch02.util.max

fun main() {
  runSection1()
}

fun runSection1() {
  val a = 3
  val b = 5
  println("The maximum value between $a and $b is ${max(3, 5)}.")
}
