all: bTree

bTree: b_Tree_main.cpp bTree.h bTreeNode.h bTreeNode.cpp

	g++ -o bTree bTreee_main.cpp bTree.h bTreeNode.h bTreeNode.cpp


clean:
	rm -rf bTree.exe
