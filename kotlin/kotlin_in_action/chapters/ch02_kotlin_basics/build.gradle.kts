import javax.inject.Inject
import org.gradle.api.DefaultTask
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.tasks.Classpath
import org.gradle.api.tasks.TaskAction
import org.gradle.process.ExecOperations

plugins {
    kotlin("jvm") version "2.3.21"
    id("com.diffplug.spotless") version "8.8.0"
}

abstract class KtfmtStdinTask @Inject constructor(private val execOperations: ExecOperations) :
    DefaultTask() {
    @get:Classpath abstract val ktfmtClasspath: ConfigurableFileCollection

    @TaskAction
    fun format() {
        val path = project.providers.gradleProperty("ktfmtPath").orNull.orEmpty()
        val sourceFile =
            temporaryDir.resolve(
                if (path.endsWith(".gradle.kts")) "stdin.gradle.kts" else "stdin.kt"
            )
        sourceFile.writeBytes(System.`in`.readBytes())

        execOperations.javaexec {
            mainClass.set("com.facebook.ktfmt.cli.Main")
            classpath = ktfmtClasspath
            args("--kotlinlang-style", sourceFile.absolutePath)
            standardOutput = System.err
        }

        System.out.write(sourceFile.readBytes())
    }
}

group = "com.shuyangsun.notes.ktinaction.ch02"

version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test"))
}

val ktfmtCli by configurations.creating

dependencies {
    ktfmtCli("com.facebook:ktfmt:0.64")
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

tasks.register<KtfmtStdinTask>("ktfmtStdin") {
    ktfmtClasspath.from(ktfmtCli)
}
