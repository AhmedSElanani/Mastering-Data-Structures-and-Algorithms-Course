#pragma once

#include <functional>
#include <memory>
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
      T&& firstValue, Rem&&... remValues)
      : m_root{std::make_unique<trees_internal::BinaryNode<T>>(
            std::forward<T>(firstValue))} {
    // check if there are other elements passed after the root element
    std::initializer_list<T> remainingElements{remValues...};
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

    for (auto const& elem : remainingElements) {
      auto& leftSubTree{helperQueue.front().get()->leftChild()};
      if (leftSubTree == nullptr) {
        leftSubTree = std::make_unique<trees_internal::BinaryNode<T>>(elem);
        helperQueue.push(leftSubTree);  // so that the left subtree takes the
                                        // first turn in the queue
      } else {
        auto& rightSubTree{helperQueue.front().get()->rightChild()};
        rightSubTree = std::make_unique<trees_internal::BinaryNode<T>>(elem);
        helperQueue.pop();  // as at this point, the queue front both children
                            // are filled
        helperQueue.push(rightSubTree);  // so that the right subtree takes the
                                         // second turn in the queue
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
private:
  /// @brief owning pointer to the root of the tree
  std::unique_ptr<trees_internal::BinaryNode<T>> m_root{nullptr};
};

}  // namespace data_structures
