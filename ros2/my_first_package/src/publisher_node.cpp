#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>

using namespace std::chrono_literals;

class MyPublisher : public rclcpp::Node
{
public:
    MyPublisher() : Node("my_publisher"), count_(0)
    {
        // 创建发布者，主题名为 "my_topic"，队列大小 10
        publisher_ = this->create_publisher<std_msgs::msg::String>("my_topic", 10);
        
        // 创建定时器，每 500ms 发布一次消息
        timer_ = this->create_wall_timer(
            500ms, std::bind(&MyPublisher::timer_callback, this));
        
        RCLCPP_INFO(this->get_logger(), "Publisher node started!");
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello ROS2! Count: " + std::to_string(count_++);
        
        // 发布消息
        publisher_->publish(message);
        
        // 打印日志
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    }
    
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
    // 初始化 ROS2
    rclcpp::init(argc, argv);
    
    // 创建节点并保持运行
    auto node = std::make_shared<MyPublisher>();
    rclcpp::spin(node);
    
    // 清理资源
    rclcpp::shutdown();
    return 0;
}