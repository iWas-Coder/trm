#
# GNU trm --- A transactional POSIX’s rm command
# Copyright (C) 2024 Wasym A. Alonso
#
# This file is part of trm.
#
# trm is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# trm is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with trm.  If not, see <http://www.gnu.org/licenses/>.
#


PPO_MKDIR = MKDIR
PPO_CLEAN = CLEAN
PPO_CXX   = CXX
PPO_LD    = LD

BUILD_DIR = build
HDR_DIR   = include
SRC_DIR   = src
OUT       = trm

OPTIMIZATIONS = -pipe -O3

CXX      = clang++
CPPFLAGS = -I $(HDR_DIR)
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Werror $(OPTIMIZATIONS)
LDFLAGS  = -lcrypto -static-libgcc -static-libstdc++ $(OPTIMIZATIONS)

SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean mrproper

all: $(BUILD_DIR) $(OUT)
	@:

$(BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(OUT): $(OBJS)
	@echo "  $(PPO_LD)      $@"
	@$(CXX) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -MD $< -o $@

-include $(BUILD_DIR)/*.d

clean:
	@if [ -d $(BUILD_DIR) ]; then           \
	  echo "  $(PPO_CLEAN)   $(BUILD_DIR)"; \
	  rm -r $(BUILD_DIR);                   \
	fi

mrproper: clean
	@if [ -e $(OUT) ]; then           \
	  echo "  $(PPO_CLEAN)   $(OUT)"; \
	  rm $(OUT);                      \
	fi
