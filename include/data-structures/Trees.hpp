#pragma once

#include <format>
#include <functional>
#include <memory>
#include <optional>
#include <queue>
#include <ranges>
#include <vector>

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief namespace for internal trees implementation
namespace trees_internal {

/// @brief class definition for Node type that can have maximum degree of two
/// @tparam T type of value to hold
template <typename T>
class BinaryNode {
public:
  /// @brief parametrized constructor of the class accepting value and
  ///        optional pointer to the next node
  /// @param value the data to be held by the node
  constexpr explicit BinaryNode(T value) : m_value{std::move(value)} {}

  /// @brief method to return value stored in this node
  /// @return the value stored in this node
  auto value() const noexcept -> T { return m_value; }

  /// @brief a method to return node's left child
  /// @return node's left child
  auto leftChild() noexcept -> std::unique_ptr<BinaryNode>& { return m_lChild; }

  /// @brief a method to return node's right child
  /// @return node's right child
  auto rightChild() noexcept -> std::unique_ptr<BinaryNode>& {
    return m_rChild;
  }

private:
  /// @brief member to hold the data value of this node
  T m_value{};

  /// @brief  member to point to the left child node if any
  std::unique_ptr<BinaryNode> m_lChild{nullptr};

  /// @brief  member to point to the right child node if any
  std::unique_ptr<BinaryNode> m_rChild{nullptr};
};

}  // namespace trees_internal

/// @brief class definition for BinaryTree data structure
/// @tparam T type of values to hold
template <typename T>
class BinaryTree {
public:
  /// @brief default constructor of the binary tree, the state after it's called
  ///        is having zero nodes in the tree
  constexpr BinaryTree() = default;

  /// @brief parametrized constructor to the binary tree, accepting one or
  ///        more values of the same type, where each of them will be
  ///        represented by an individual node
  /// @tparam ...Rem remaining values passed if any
  /// @param firstValue data to initialize the root node
  /// @param ...remValues data to initialize the remaining nodes in if any
  /// @note this guarantees that first and remaining values are of same type
  template <typename... Rem>
  constexpr explicit BinaryTree(
      // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved,-warnings-as-errors)
      std::optional<T>&& firstValue, Rem&&... remValues)
      : m_root{{// Note: static assertion wasn't possible since firstValue is
                // not a constant expression. The next best thing is adding a
                // ternary operator for checking if the first argument has a
                // value, followed by a null check for the tree root.
                firstValue.has_value()
                    ? std::make_unique<trees_internal::BinaryNode<T>>(
                          std::forward<T>(firstValue.value()))
                    : nullptr}} {
    if (m_root == nullptr) {
      return;
    }

    // check if there are other elements passed after the root element
    std::initializer_list<std::optional<T>> remainingElements{remValues...};
    if constexpr (constexpr auto kNoOfRemainingElements{
                      sizeof(remainingElements)};
                  kNoOfRemainingElements == 0U) {
      return;
    }

    // Below algorithm fills the tree in a Level order

    // Note: constructing the queue from root had to be done on two steps as
    // std::queue doesn't define a constructor that accepts element directly
    std::queue<std::reference_wrapper<
        std::unique_ptr<trees_internal::BinaryNode<T>> const>>
        helperQueue;
    helperQueue.push(m_root);

    // define an enum for turns between subtrees and declare a variable of it
    enum class subtreeTurn {
      leftSubtree,
      rightSubtree,
    };

    for (auto subtreeTurn{// init to right tree, so that on the first iteration
                          // it switches and starts with left
                          subtreeTurn::rightSubtree};
         auto const& elem : remainingElements) {
      if (helperQueue.empty()) {
        // this means there are no leaf nodes available to hold remaining
        // elements
        break;
      }

      // Note: switching turns is done at the beginning and not the end so that
      // if the iteration is skipped due to std::nullopt element, still turns
      // are preserved
      subtreeTurn = {subtreeTurn == subtreeTurn::leftSubtree
                         ? subtreeTurn::rightSubtree
                         : subtreeTurn::leftSubtree};

      if (elem == std::nullopt) {
        // this subtree will be skipped

        if (subtreeTurn == subtreeTurn::rightSubtree) {
          // if we reached the right side of this node, then it's done
          helperQueue.pop();
        }

        continue;
      }

      if (subtreeTurn == subtreeTurn::leftSubtree) {
        auto& leftSubTree{helperQueue.front().get()->leftChild()};
        leftSubTree =
            std::make_unique<trees_internal::BinaryNode<T>>(elem.value());
        helperQueue.push(leftSubTree);  // so that the left subtree takes the
                                        // first turn in the queue
      } else {
        // assuming the only other possible option is right subtree
        auto& rightSubTree{helperQueue.front().get()->rightChild()};
        rightSubTree =
            std::make_unique<trees_internal::BinaryNode<T>>(elem.value());
        helperQueue.push(rightSubTree);  // so that the right subtree takes the
                                         // second turn in the queue

        // if we reached the right side of this node, then it's done
        helperQueue.pop();
      }
    }
  }

  /// @brief method to traverse the tree in PreOrder
  /// @return vector of the nodes' values in PreOrder
  std::vector<T> traversePreOrder() const noexcept {
    if (m_root == nullptr) {
      return std::vector<T>{};
    }

    std::function<std::vector<T>(
        std::unique_ptr<trees_internal::BinaryNode<T>> const&)> const
        traversePreOrderInternal{[&traversePreOrderInternal](
                                     auto const& startNode) {
          if (startNode == nullptr) {
            return std::vector<T>{};
          }

          std::vector<T> nodesValues;
          nodesValues.emplace_back(startNode->value());

          std::ranges::move(traversePreOrderInternal(startNode->leftChild()),
                            std::back_inserter(nodesValues));

          std::ranges::move(traversePreOrderInternal(startNode->rightChild()),
                            std::back_inserter(nodesValues));

          return nodesValues;
        }};

    return traversePreOrderInternal(m_root);
  }

  /// @brief method to traverse the tree in order
  /// @return vector of the nodes' values in order
  std::vector<T> traverseInOrder() const noexcept {
    if (m_root == nullptr) {
      return std::vector<T>{};
    }

    std::function<std::vector<T>(
        std::unique_ptr<trees_internal::BinaryNode<T>> const&)> const
        traverseInOrderInternal{[&traverseInOrderInternal](
                                    auto const& startNode) {
          if (startNode == nullptr) {
            return std::vector<T>{};
          }

          std::vector<T> nodesValues;

          std::ranges::move(traverseInOrderInternal(startNode->leftChild()),
                            std::back_inserter(nodesValues));

          nodesValues.emplace_back(startNode->value());

          std::ranges::move(traverseInOrderInternal(startNode->rightChild()),
                            std::back_inserter(nodesValues));

          return nodesValues;
        }};

    return traverseInOrderInternal(m_root);
  }

  /// @brief method to traverse the tree in PostOrder
  /// @return vector of the nodes' values in PostOrder
  std::vector<T> traversePostOrder() const noexcept {
    if (m_root == nullptr) {
      return std::vector<T>{};
    }

    std::function<std::vector<T>(
        std::unique_ptr<trees_internal::BinaryNode<T>> const&)> const
        traversePostOrderInternal{[&traversePostOrderInternal](
                                      auto const& startNode) {
          if (startNode == nullptr) {
            return std::vector<T>{};
          }

          std::vector<T> nodesValues;

          std::ranges::move(traversePostOrderInternal(startNode->leftChild()),
                            std::back_inserter(nodesValues));

          std::ranges::move(traversePostOrderInternal(startNode->rightChild()),
                            std::back_inserter(nodesValues));

          nodesValues.emplace_back(startNode->value());

          return nodesValues;
        }};

    return traversePostOrderInternal(m_root);
  }

  /// @brief method to traverse the tree in level order
  /// @return vector of the nodes' values in level order
  std::vector<T> traverseLevelOrder() const noexcept {
    if (m_root == nullptr) {
      return std::vector<T>{};
    }

    std::queue<std::reference_wrapper<
        std::unique_ptr<trees_internal::BinaryNode<T>> const>>
        helperQueue;
    helperQueue.push(m_root);

    std::vector<T> nodesValues;
    while (helperQueue.empty() == false) {
      const auto& currentNode{helperQueue.front().get()};

      if (currentNode->leftChild()) {
        helperQueue.push(currentNode->leftChild());
      }

      if (currentNode->rightChild()) {
        helperQueue.push(currentNode->rightChild());
      }

      nodesValues.emplace_back(currentNode->value());
      helperQueue.pop();
    }

    return nodesValues;
  }

  /// @brief method to return the count of nodes in the tree
  /// @return the count of nodes in the tree
  /// @note another possible implementation is having an instance member that is
  ///       incremented upon creating a new node and returning this member when
  ///       calling this method
  constexpr std::size_t count() const noexcept {
    if (m_root == nullptr) {
      // this means the tree is empty
      return 0U;
    }

    std::function<std::size_t(
        std::unique_ptr<trees_internal::BinaryNode<T>> const&)> const
        countNodes{[&countNodes](auto const& startNode) {
          if (startNode == nullptr) {
            // this means you tried to branch of a leaf node
            return static_cast<std::size_t>(0U);
          }

          // count this node plus nodes of left and right subtrees
          return static_cast<std::size_t>(1U) +
                 countNodes(startNode->leftChild()) +
                 countNodes(startNode->rightChild());
        }};

    return countNodes(m_root);
  }


  /// @brief enum class to be used as parameter to display method to specify the
  ///        order of traversal
  enum class traversalOrder : std::uint8_t {
    preOrder,
    inOrder,
    postOrder,
    levelOrder,
  };

  /// @brief method to display elements of the tree based on the traversal order
  ///        passed
  /// @param order
  /// @return elements of the tree surrounded by braces
  [[nodiscard]] constexpr auto display(traversalOrder order) const noexcept
      -> std::string {
    std::vector<T> nodesValues;
    switch (order) {
      case traversalOrder::preOrder: {
        nodesValues = traversePreOrder();
      } break;
      case traversalOrder::inOrder: {
        nodesValues = traverseInOrder();
      } break;
      case traversalOrder::postOrder: {
        nodesValues = traversePostOrder();
      } break;
      case traversalOrder::levelOrder: {
        nodesValues = traverseLevelOrder();
      } break;

      default: {
        // keep the vector empty
      } break;
    }

    const auto stringify{[](auto elements) {
      std::string result;
      for (auto it{elements.begin()}; it != elements.end(); ++it) {
        result += std::to_string(*it) + (it == elements.end() - 1U ? "" : ",");
      }

      return result;
    }};

    return std::string{std::format("{{{}}}", stringify(nodesValues))};
  }

private:
  /// @brief owning pointer to the root of the tree
  std::unique_ptr<trees_internal::BinaryNode<T>> m_root{nullptr};
};

}  // namespace data_structures
