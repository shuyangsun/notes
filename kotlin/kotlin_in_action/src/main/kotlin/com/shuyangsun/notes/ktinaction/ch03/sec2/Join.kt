@file:JvmName("StringFunctions")

package com.shuyangsun.notes.ktinaction.ch03.sec2

fun <T> joinToString(
  collection: Collection<T>,
  separator: String = ", ",
  prefix: String = "[",
  postfix: String = "]",
): String {
  val result = StringBuilder(prefix)
  for ((i, ele) in collection.withIndex()) {
    if (i > 0) {
      result.append(separator)
    }
    result.append(ele)
  }
  result.append(postfix)
  return result.toString()
}
