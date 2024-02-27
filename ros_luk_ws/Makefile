.PHONY: build

rosdep:
	rosdep install -i --from-path src --rosdistro humble -y

build:
	colcon build --packages-select py_pubsub