data class Person(
    val name: String,
    val age: Int? = null
)

fun main() {
    val persons = listOf(
        Person("Shuyang", age=32),
        Person("Bob")
    )
    val oldest = persons.maxBy { it.age ?: 0 }
    println("The oldest is: $oldest")
}

