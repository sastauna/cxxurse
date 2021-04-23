ifeq ($(OS), Windows_NT)
	exe := exe
else
	exe := elf
endif

# c
c_flags   = $(shell ./space_cat.$(exe) c/compile_flags.txt)
c_dflags := -g
c_rflags := -O2

.SECONDARY:

space_cat.$(exe): c/space_cat.c
	clang $< -Wall -Wextra -Ofast -fuse-ld=lld -o $@

## base
c/%.$(exe): c/%.c
	clang $< $(c_flags) -o $@

run~%.c: c/%.$(exe)
	@./$<

## debug
c/%.debug.$(exe): c/%.c
	clang $< $(c_flags) $(c_dflags) -o $@

debug~%.c: c/%.debug.$(exe)
	-

## release
c/%.release.$(exe): c/%.c
	clang $< $(c_flags) $(c_rflags) -o $@

release~%.c: c/%.release.$(exe)
	-

# cxx
cxx_flags  := $(shell ./space_cat.$(exe) cxx/compile_flags.txt)
cxx_dflags := -g
cxx_rflags := -O2

## base
cxx_base = clang++ $< $(cxx_flags) -o $@

cxx/%.$(exe): cxx/%.cxx
	$(cxx_base)

run~%.cxx: cxx/%.$(exe)
	@-./$<

## debug
cxx_debug = clang++ $< $(cxx_flags) $(cxx_dflags) -o $@

cxx/%.debug.$(exe): cxx/%.cxx
	$(cxx_debug)

debug~%.cxx: cxx/%.debug.$(exe)
	-

## release
cxx_release = clang++ $< $(cxx_flags) $(cxx_rflags) -o $@
cxx/%.release.$(exe): cxx/%.cxx
	-$(cxx_release)

release~%.cxx: cxx/%.release.$(exe)
	-

clean-artifacts: run~clean_artifacts.cxx
	-

### cxx_weekly
cxx/weekly/%.$(exe): cxx/weekly/%.cxx
	$(cxx_base)

num_to_exe = $(patsubst %.cxx,%.$(exe),$(wildcard cxx/weekly/*$(1).*.cxx))

.SECONDEXPANSION:
cxx_weekly~%: $$(call num_to_exe,%)
	@-./$<

.PHONY: cxx_weekly~%
