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

CXX           = clang++
OPTIMIZATIONS = -pipe -O3

TRM_HDR_DIR   = include
TRM_SRC_DIR   = src
TRM_BUILD_DIR = build
TRM_SRCS     := $(wildcard $(TRM_SRC_DIR)/*.cc)
TRM_OBJS     := $(patsubst $(TRM_SRC_DIR)/%.cc, $(TRM_BUILD_DIR)/%.o, $(TRM_SRCS))
TRM_CPPFLAGS  = -I $(TRM_HDR_DIR)
TRM_CXXFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic -Werror $(OPTIMIZATIONS)
TRM_LDFLAGS   = -lcrypto -static-libgcc -static-libstdc++ $(OPTIMIZATIONS)
TRM_OUT       = trm

.PHONY: all clean mrproper

all: $(TRM_BUILD_DIR) $(TRM_OUT)
	@:

$(TRM_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(TRM_OUT): $(TRM_OBJS)
	@echo "  $(PPO_LD)      $@"
	@$(CXX) $^ $(TRM_LDFLAGS) -o $@

$(TRM_BUILD_DIR)/%.o: $(TRM_SRC_DIR)/%.cc
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(TRM_CPPFLAGS) $(TRM_CXXFLAGS) -c -MD $< -o $@

-include $(TRM_BUILD_DIR)/*.d

clean:
	@if [ -d $(TRM_BUILD_DIR) ]; then           \
	  echo "  $(PPO_CLEAN)   $(TRM_BUILD_DIR)"; \
	  rm -r $(TRM_BUILD_DIR);                   \
	fi

mrproper: clean
	@if [ -e $(TRM_OUT) ]; then           \
	  echo "  $(PPO_CLEAN)   $(TRM_OUT)"; \
	  rm $(TRM_OUT);                      \
	fi
