src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

args = -Wall -g

ALL:a.out

a.out: $(obj)
	gcc $^ -o $@ $(args)

$(obj):%.o:%.c
	gcc -c $< -o $@ $(args)

clean:
	-rm -rf $(obj) a.out

.PHONY: clean ALL

git:
	@git add .
	@git commit -m "update mmap and add signal "
	@git push origin master
