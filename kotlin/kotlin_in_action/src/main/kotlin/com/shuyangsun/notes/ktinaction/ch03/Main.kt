package com.shuyangsun.notes.ktinaction.ch03

import com.shuyangsun.notes.ktinaction.ch03.sec2.*

fun main() {
  runSec1()
  runSec2()
}

fun runSec1() {
  val set = setOf(1, 7, 53)
  val list = listOf(1, 7, 53)
  val map = mapOf(1 to "one", 7 to "seven", 53 to "fifty-three")

  println(set.javaClass)
  println(list.javaClass)
  println(map.javaClass)
}

fun runSec2() {
  println(joinToString(listOf(1, 2, 3)))
}
