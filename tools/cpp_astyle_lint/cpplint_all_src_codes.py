#!/usr/bin/python
#-*-coding:utf-8-*-

import os
import os.path

need_cpplint_dir = '..\..'
ignore_lists="-legal/copyright"

for parent,dirnames,filenames in os.walk(need_cpplint_dir):
	for filename in filenames:
		need_astyle_file = os.path.join(parent,filename)
		if need_astyle_file.endswith(('.cpp','.h','.CPP','.H','.Cpp', '.hpp')):
			#print need_astyle_file
			os.system("python %s --filter=%s %s" % ('.\\cpplint.py',ignore_lists,need_astyle_file))