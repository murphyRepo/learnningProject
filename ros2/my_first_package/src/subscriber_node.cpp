#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MySubscriber : public rclcpp::Node
{
public:
    MySubscriber() : Node("my_subscriber")
    {
        // 创建订阅者，主题名为 "my_topic"，队列大小 10
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "my_topic",
            10,
            std::bind(&MySubscriber::topic_callback, this, _1));
        
        RCLCPP_INFO(this->get_logger(), "Subscriber node started!");
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        // 接收到消息时调用
        RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
    }
    
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MySubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}