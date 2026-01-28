from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='my_first_package',
            executable='publisher_node',
            name='my_publisher'
        ),
        Node(
            package='my_first_package',
            executable='subscriber_node',
            name='my_subscriber'
        )
    ])