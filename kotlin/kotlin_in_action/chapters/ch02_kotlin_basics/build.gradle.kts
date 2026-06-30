plugins {
    kotlin("jvm") version "2.3.21"
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

tasks.test {
    useJUnitPlatform()
}