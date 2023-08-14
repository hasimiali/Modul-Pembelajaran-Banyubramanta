// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_message:msg/Sphere.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MESSAGE__MSG__DETAIL__SPHERE__BUILDER_HPP_
#define CUSTOM_MESSAGE__MSG__DETAIL__SPHERE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_message/msg/detail/sphere__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_message
{

namespace msg
{

namespace builder
{

class Init_Sphere_radius
{
public:
  explicit Init_Sphere_radius(::custom_message::msg::Sphere & msg)
  : msg_(msg)
  {}
  ::custom_message::msg::Sphere radius(::custom_message::msg::Sphere::_radius_type arg)
  {
    msg_.radius = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_message::msg::Sphere msg_;
};

class Init_Sphere_center
{
public:
  Init_Sphere_center()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Sphere_radius center(::custom_message::msg::Sphere::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_Sphere_radius(msg_);
  }

private:
  ::custom_message::msg::Sphere msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_message::msg::Sphere>()
{
  return custom_message::msg::builder::Init_Sphere_center();
}

}  // namespace custom_message

#endif  // CUSTOM_MESSAGE__MSG__DETAIL__SPHERE__BUILDER_HPP_
