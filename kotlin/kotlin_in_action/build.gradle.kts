import java.io.ByteArrayOutputStream
import java.io.File
import java.io.OutputStream
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
    val suffix = if (path.endsWith(".gradle.kts")) ".gradle.kts" else ".kt"
    val sourceFile = File.createTempFile("stdin-", suffix, temporaryDir)
    sourceFile.writeBytes(System.`in`.readBytes())

    val ktfmtErrorOutput = ByteArrayOutputStream()
    val result = execOperations.javaexec {
      mainClass.set("com.facebook.ktfmt.cli.Main")
      classpath = ktfmtClasspath
      args("--google-style", sourceFile.absolutePath)
      isIgnoreExitValue = true
      standardOutput = OutputStream.nullOutputStream()
      errorOutput = ktfmtErrorOutput
    }
    if (result.exitValue != 0) {
      System.err.write(ktfmtErrorOutput.toByteArray())
      result.assertNormalExitValue()
    }

    System.out.write(sourceFile.readBytes())
  }
}

group = "com.shuyangsun.notes.ktinaction"

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
    target("src/**/*.kt")
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
