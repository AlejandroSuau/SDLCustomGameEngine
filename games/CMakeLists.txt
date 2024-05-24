INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(
    spark_propagation
    spark_propagation/src/Grid.cpp
    spark_propagation/src/SparkPropagation.cpp
)