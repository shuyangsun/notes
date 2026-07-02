package com.shuyangsun.notes.ktinaction.ch02.sec3

enum class ProgrammingLanguage {
  KOTLIN,
  JAVA,
  C,
  CPP,
  RUST,
  GO,
  PYTHON,
  JAVASCRIPT,
}

val langToCompiled: Map<ProgrammingLanguage, Boolean> =
  mapOf(
    ProgrammingLanguage.KOTLIN to true,
    ProgrammingLanguage.JAVA to true,
    ProgrammingLanguage.C to true,
    ProgrammingLanguage.CPP to true,
    ProgrammingLanguage.RUST to true,
    ProgrammingLanguage.GO to true,
    ProgrammingLanguage.PYTHON to false,
    ProgrammingLanguage.JAVASCRIPT to false,
  )
