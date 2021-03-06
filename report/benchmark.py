import streamlit as st
import pandas as pd
import numpy as np
import json

st.title("Benchmark of matrix multiplications")


@st.cache
def load_data():
    with open("report/bench.json", "r") as f:
        data = json.load(f)
    return data


benchmark_data = load_data()

st.caption(f"Builded as {benchmark_data['context']['library_build_type']}")

st.header("Full benchmark data")

with st.expander("See details"):
    st.json(benchmark_data)

st.header("CPU information")

st.markdown(f"`Hostname`: {benchmark_data['context']['host_name']}")
st.markdown(f"`N° cpu(s)`: {benchmark_data['context']['num_cpus']}")
st.markdown(f"`MHz/cpu`: {benchmark_data['context']['mhz_per_cpu']}")
st.markdown(
    f"`CPU Scaling enabled`: {benchmark_data['context']['cpu_scaling_enabled']}"
)

st.subheader("Caches info")

caches = benchmark_data["context"]["caches"]
caches_column = st.columns(len(caches))

# Get cache and index
for index, cache in enumerate(caches_column):
    cache.metric(
        f"Level {caches[index]['level']}",
        f"{caches[index]['type']}",
        f"{caches[index]['size']} bits",
    )


def separate_benchmark_data(benchmarks):
    """
    Separate the benchmark data into a dictonary.
    """

    separated_benchmarks = {}
    for benchmark in benchmarks:
        name, size = benchmark["run_name"].split("/")
        operation = benchmark["aggregate_name"]

        if name not in separated_benchmarks:
            separated_benchmarks[name] = {}

        if size not in separated_benchmarks[name]:
            separated_benchmarks[name][size] = {}

        separated_benchmarks[name][size][operation] = benchmark["real_time"]

    return separated_benchmarks


separated_benchmarks = separate_benchmark_data(benchmark_data["benchmarks"])

# Store specifically the data from BM_Multiplication and BM_TransposedMultiplication
multiplication = []
transposed_multiplication = []
matrix_sizes = []

# Create a chart for each benchmark based on the size of the matrix
for benchmark_name, benchmark_data in separated_benchmarks.items():
    st.header(f"{benchmark_name}")

    # Create a chart for each operation where the x axis is the size of the matrix and the y axis is the time
    matrix_size = []
    real_time = []

    current_operation = 0

    for size, data in benchmark_data.items():
        matrix_size.append(int(size))

        operation_times = []
        for operation, time in data.items():
            operation_times.append(time * 10e-9)

        real_time.append(operation_times)

        current_operation += 1

    # Store the data for the comparison
    matrix_sizes = matrix_size

    chart_data = pd.DataFrame(
        real_time, index=matrix_size, columns=["mean", "median", "stddev"]
    )

    st.line_chart(chart_data)

    # If the benchmark is BM_Multiplication or BM_TransposedMultiplication, store the data
    if benchmark_name == "BM_Multiplication":
        multiplication = real_time
    elif benchmark_name == "BM_TransposedMultiplication":
        transposed_multiplication = real_time


st.header("Comparison")

col1, col2 = st.columns(2)

with col1:
    st.subheader("Normal multiplication real time")
    st.line_chart(
        pd.DataFrame(
            multiplication, index=matrix_sizes, columns=["mean", "median", "stddev"]
        )
    )

with col2:
    st.subheader("Transposed multiplication real time")
    st.line_chart(
        pd.DataFrame(
            transposed_multiplication,
            index=matrix_sizes,
            columns=["mean", "median", "stddev"],
        )
    )

st.header("Speedup")


is_inverted = st.checkbox("Invert the speedup")

title = f"To calculate the speedup from both benchmarks, we need to divide the time of the {'normal' if is_inverted else 'transposed'} multiplication by the time of the {'tranposed' if is_inverted else 'normal'} multiplication."

st.write(title)

if is_inverted:
    st.latex(
        r"""
        speedup = \frac{normal\_time}{transposed\_time}
        """
    )
else:
    st.latex(
        r"""
        speedup = \frac{transposed\_time}{normal\_time}
        """
    )

# Calculate the speedup for each matrix size
speedup = []
for index, size in enumerate(matrix_sizes):
    mult = multiplication[index][0]
    transp = transposed_multiplication[index][0]
    result = (mult / transp) if is_inverted else (transp / mult)
    speedup.append(result)

# Plot the speedup
st.line_chart(
    pd.DataFrame(
        speedup,
        index=matrix_sizes,
        columns=["speedup"],
    )
)
