cxx := clang++

ifeq ($(OS), Windows_NT)
	exe := exe
else
	exe := elf
endif

.SECONDARY:
.SECONDEXPANSION:

# cxx
cxx_flags  := $(shell ./misc/space_cat.$(exe) compile_flags.txt)
cxx_dflags := $(cxx_flags) -g
cxx_rflags := $(cxx_flags) -O2

match_exe = $(patsubst src/%.cxx,bin/%.$(2),$(wildcard src/$(1)*.cxx))

# base
bin/%.$(exe): src/%.cxx
	$(cxx) $< $(cxx_flags) -o $@

run~%: $$(call match_exe,%,$(exe))
	./$<

# debug
bin/%.debug.$(exe): src/%.cxx
	$(cxx) $< $(cxx_dflags) -o $@

debug~%: $$(call match_exe,%,$(exe))
	-

# release
bin/%.release.$(exe): src/%.cxx
	$(cxx) $< $(cxx_rflags) -o $@

release~%: $$(call match_exe,%,$(exe))
	-
