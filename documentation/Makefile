

SRC_COMMON := $(shell find ../src/Common -name '*.[cpp,h]*' | sort)
SRC_COMMON += $(shell find ../src/Defines -name '*.[cpp,h]*' | sort)
SRC_CLIENT := $(shell find ../src/Client -name '*.[cpp,h]*' | sort)
SRC_SERVER := $(shell find ../src/Server -name '*.[cpp,h]*' | sort)
SRC_EDITOR := $(shell find ../src/Editor -name '*.[cpp,h]*' | sort)
SRC_COMMONUI := $(shell find ../src/CommonUI -name '*.[cpp,h]*' | sort)



# REGLAS
#########

.PHONY: all

all: client server editor common commonui

pdf: all

client: $(SRC_CLIENT)
	a2ps $(SRC_CLIENT) --title="Grupo 4" -Av --header="[75.42] Taller de programacion" --footer="Tp final - Worms" --line-numbers=1 --borders=yes --columns=2  --landscape --output=out.ps --encoding=ISO-8859-1 --tabsize=4 --major=columns --toc
	ps2pdf out.ps client.pdf
	rm out.ps

server: $(SRC_SERVER)
	a2ps $(SRC_SERVER) --title="Grupo 4" -Av --header="[75.42] Taller de programacion" --footer="Tp final - Worms" --line-numbers=1 --borders=yes --columns=2  --landscape --output=out.ps --encoding=ISO-8859-1 --tabsize=4 --major=columns --toc
	ps2pdf out.ps server.pdf
	rm out.ps

editor: $(SRC_EDITOR)
	a2ps $(SRC_EDITOR) --title="Grupo 4" -Av --header="[75.42] Taller de programacion" --footer="Tp final - Worms" --line-numbers=1 --borders=yes --columns=2  --landscape --output=out.ps --encoding=ISO-8859-1 --tabsize=4 --major=columns --toc
	ps2pdf out.ps editor.pdf
	rm out.ps

common: $(SRC_COMMON)
	a2ps $(SRC_COMMON) --title="Grupo 4" -Av --header="[75.42] Taller de programacion" --footer="Tp final - Worms" --line-numbers=1 --borders=yes --columns=2  --landscape --output=out.ps --encoding=ISO-8859-1 --tabsize=4 --major=columns --toc
	ps2pdf out.ps common.pdf
	rm out.ps

commonui: $(SRC_COMMONUI)
	a2ps $(SRC_COMMONUI) --title="Grupo 4" -Av --header="[75.42] Taller de programacion" --footer="Tp final - Worms" --line-numbers=1 --borders=yes --columns=2  --landscape --output=out.ps --encoding=ISO-8859-1 --tabsize=4 --major=columns --toc
	ps2pdf out.ps commonui.pdf
	rm out.ps
