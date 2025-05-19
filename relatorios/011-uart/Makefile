# BOARD=arduino:avr:uno
# EXERCICIOS = $(wildcard exercicio*/)
# all: clean build
# build: $(EXERCICIOS)
# $(EXERCICIOS):
# 	arduino-cli compile -b $(BOARD) $(@F) --output-dir ./build/$(@F)
# clean:
# 	rm -rf ./build

BOARD=arduino:avr:uno
EXERCIOS=$(wildcard exercicio*/)

all: clean build

build:
	@for dir in $(EXERCIOS); do \
		name=$$(basename $$dir); \
		echo "Compilando $$name..."; \
		arduino-cli compile -b $(BOARD) $$dir --output-dir ./build/$$name; \
	done

clean:
	rm -rf ./build
