all: bazeltest

bazeltest:
	bazel test test/match_test --test_output=all
