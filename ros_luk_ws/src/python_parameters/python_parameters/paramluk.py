import rclpy
import rclpy.node

class ParamLuk(rclpy.node.Node):
    def __init__(self):
        super().__init__('minimal_param_node')

        self.declare_parameter('is_luk_happy', 'yes!')

        self.timer = self.create_timer(1, self.timer_callback)

    def timer_callback(self):
        my_param = self.get_parameter('is_luk_happy').get_parameter_value().string_value

        self.get_logger().info('param is (%s)' % my_param)

        my_new_param = rclpy.parameter.Parameter(
            'is_luk_happy',
            rclpy.Parameter.Type.STRING,
            'yes'
        )
        all_new_parameters = [my_new_param]
        self.set_parameters(all_new_parameters)

def main():
    rclpy.init()
    node = ParamLuk()
    rclpy.spin(node)

if __name__ == '__main__':
    main()