#!/bin/sh

if git rev-parse --verify HEAD >/dev/null 2>&1
then
	against=HEAD
else
	# Initial commit: diff against an empty tree object
	against=4b825dc642cb6eb9a060e54bf8d69288fbee4904
fi

# We should pass only added or modified C/C++ source files to cppcheck.
changed_files=$(git diff-index --cached $against | \
	grep -E '[MA]	.*\.(c|cpp|h|hpp)$' | \
	grep -v 'glog' | \
	cut -d'	' -f 2)

ignore_lists="-legal/copyright,-build/include_what_you_use"

cpp_astyle_lint_Dir="./tools/cpp_astyle_lint"

lint_ret=0
if [ -n "$changed_files" ]; then	
	python $cpp_astyle_lint_Dir/cpplint.py --filter=$ignore_lists $changed_files
	lint_ret=$?
	if [ "$lint_ret" != 0 ]; then
		echo -e "[提交失败!!!]\n上传的代码中存在一些不规范的地方, 请手动修改并提交, 直到所有代码都符合规范为止..."
	fi
	exit $lint_ret
fi
