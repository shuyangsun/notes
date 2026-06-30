package com.shuyangsun.notes.ktinaction.ch02.sec3

interface Expr
class Num(val value: Int): Expr {
  override fun toString(): String = "$value"
}
class Sum(val lhs: Expr, val rhs: Expr): Expr {
  override fun toString(): String = "$lhs + $rhs"
}

fun eval(e: Expr): Result<Int> =
  when (e) {
    is Num -> Result.success(e.value)
    is Sum -> {
      val result = Pair(eval(e.lhs), eval(e.rhs))
      when {
        result.first.isFailure -> result.first
        result.second.isFailure -> result.first
        else -> Result.success(result.first.getOrThrow() + result.second.getOrThrow())
      }
    }
    else -> Result.failure(IllegalArgumentException("Unknown expr"))
  }
