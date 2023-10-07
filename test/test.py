import subprocess
import argparse
from subprocess import Popen, PIPE, STDOUT

comp_test_data = {
    (4, 13, 1, 2, 3, 4, 1, 2, 5, 5, 2, 4, 3, 4, 1)              : (7, 5),
    (4, 10, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2)                       : (8, 8),
    (4, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)                      : (0, 0),
    (6, 10, 1, 2, 3, 4, 4, 1, 2, 10, 7, 11)                     : (3, 3),
    (8, 16, 1, 2, 2, 1, 5, 4, 2, 1, 10, 6, 7, 8, 10, 11, 12, 5) : (5, 5),
    (5, 100, 8, 4, 1, 7, 1, 2, 3, 8, 7, 9, 0, 1, 0, 6, 10, 3,
     0, 8, 3, 6, 2, 2, 7, 6, 7, 4, 10, 3, 8, 3, 6, 7, 4, 9, 8,
     8, 5, 0, 3, 7, 3, 1, 9, 9, 7, 5, 9, 9, 9, 2, 4, 8, 1, 4,
     10, 8, 5, 0, 9, 5, 0, 5, 6, 2, 4, 1, 9, 10, 7, 2, 7, 10,
     10, 4, 0, 8, 9, 7, 3, 6, 4, 1, 5, 8, 8, 2, 7, 3, 3, 3, 2,
     7, 4, 2, 9, 7, 7, 1, 0, 5)                                 : (48, 37),
    (4, 12, 1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4)                 : (6, 4),
    (2, 7, 3, 5, 6, 2, 5, 1, 3)                                 : (1, 1)
}


def check_output_data(n_test, stdout_data, right_n_hits):
    try:
        if int(stdout_data) == right_n_hits:
            print(f"Test {n_test} Passed")
        else:
            print(f"Test {n_test} NOT Passed\n"         + \
                  f"Hits: \n\t outputted={stdout_data}" + \
                  f"\n\t right={right_n_hits}"
                  )
    except:
        print(f"Test {n_test} fail. Output of program is:\n'" + \
              stdout_data + "'"
              )


def check_comp_output_data(n_test, stdout1_data, stdout2_data, right_1n_hits, right_2n_hits):
    print("\nLFU cache")
    check_output_data(n_test, stdout1_data, right_1n_hits)

    print("\nPerfect cache")
    check_output_data(n_test, stdout2_data, right_2n_hits)


def run_cache(app2run, input_data, cmd_flags=None):
    pipe = Popen(app2run, stdout=PIPE, stdin=PIPE)

    data_str = str()
    for data in input_data:
        data_str += str(data) + " "

    stdout_data = pipe.communicate(input=bytes(data_str, "UTF-8"))

    return stdout_data[0].decode().split()


def run_cache_tests(input_data, cache_app_name2run):
    for (data, i) in zip(input_data, range(len(input_data))):
        output = run_cache(cache_app_name2run, data)

        check_comp_output_data(i, output[0], output[1], input_data[data][0], input_data[data][1])


if __name__ == "__main__":
    run_cache_tests(comp_test_data, "../cmake-build-debug/Cache")