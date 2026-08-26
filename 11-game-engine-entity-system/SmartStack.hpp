/**
 * @file SmartStack.hpp
 * @brief Header file for the generic SmartStack class
 *
 * This file contains a template stack implementation using std::unique_ptr
 * for memory management without explicit delete calls.
 */

#ifndef SMARTSTACK_HPP
#define SMARTSTACK_HPP

#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>

namespace gameengine {

    template <typename T>
    class SmartStack {
    private:
        struct Node {
            T data;
            std::unique_ptr<Node> next;
            
            // Constructors that move values (Move)
            Node(const T& val, std::unique_ptr<Node> n) : data(val), next(std::move(n)) {}
            Node(T&& val, std::unique_ptr<Node> n) : data(std::move(val)), next(std::move(n)) {}
        };

        std::unique_ptr<Node> head;
        size_t count = 0;

    public:
        SmartStack() = default;

        // Move constructor
        SmartStack(SmartStack&& other) noexcept : head(std::move(other.head)), count(other.count) {
            other.count = 0;
        }

        // Move assignment
        SmartStack& operator=(SmartStack&& other) noexcept {
            if (this != &other) {
                clear();
                head = std::move(other.head);
                count = other.count;
                other.count = 0;
            }
            return *this;
        }

        // Prevent copying
        SmartStack(const SmartStack&) = delete;
        SmartStack& operator=(const SmartStack&) = delete;

        ~SmartStack() {
            clear();
        }

        void push(const T& value) {
            head = std::make_unique<Node>(value, std::move(head));
            count++;
        }

        void push(T&& value) {
            head = std::make_unique<Node>(std::move(value), std::move(head));
            count++;
        }

        T pop() {
            if (!head) throw std::underflow_error("Stack is empty");
            T value = std::move(head->data);
            head = std::move(head->next);
            count--;
            return value;
        }

        T& top() {
            if (!head) throw std::underflow_error("Stack is empty");
            return head->data;
        }

        const T& top() const {
            if (!head) throw std::underflow_error("Stack is empty");
            return head->data;
        }

        size_t size() const { return count; }
        bool empty() const { return count == 0; }

        void clear() {
            // Iterative deletion is mandatory to prevent Stack Overflow in massive stacks
            while (head) {
                head = std::move(head->next);
            }
            count = 0;
        }

        std::string toString() const {
            if (!head) return "[]";
            std::ostringstream oss;
            oss << "[";
            Node* current = head.get();
            while (current) {
                oss << current->data;
                if (current->next) oss << ", ";
                current = current->next.get();
            }
            oss << "]";
            return oss.str();
        }

        template <typename Func>
        void forEach(Func f) {
            Node* current = head.get();
            while (current) {
                f(current->data);
                current = current->next.get();
            }
        }
    };

} // namespace gameengine

#endif // SMARTSTACK_HPP