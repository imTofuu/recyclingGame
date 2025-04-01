!#/bin/bash

originalDir="$(pwd)"

end() {
	cd "$originalDir" || exit 1
	exit 1
}

cd "$(dirname "$0")" || end
pwd

cmake -S . -B build
cmake --build build

./bin/recyclingGame/recyclingGame

end
