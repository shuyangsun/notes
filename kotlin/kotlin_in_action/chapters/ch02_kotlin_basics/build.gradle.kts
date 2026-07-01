plugins {
    kotlin("jvm") version "2.3.21"
    id("com.diffplug.spotless") version "8.8.0"
}

group = "com.shuyangsun.notes.ktinaction.ch02"

version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test"))
}

kotlin {
    jvmToolchain(25)
}

spotless {
    kotlin {
        target("../**/*.kt")
        ktfmt("0.64").kotlinlangStyle()
    }

    kotlinGradle {
        target("*.gradle.kts")
        ktfmt("0.64").kotlinlangStyle()
    }
}

tasks.test {
    useJUnitPlatform()
}
