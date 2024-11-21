#ifndef COMPLETE_BINARY_TREE_H_GUARD
#define COMPLETE_BINARY_TREE_H_GUARD

#include <cstdint>
#include <cmath>
#include "binary_tree.h"
#include "queue.h"

namespace data_struct
{
    template <typename T>
    class CompleteBinTree {
        struct Node;
        class IterImpl;

        friend IterImpl;

        using Impl = BinTree<Node>;
    
    private:
        using Self = CompleteBinTree;
        using BranchIt = typename Impl::ConstBranchIt;
    
    public:
        using ConstIterator = iter::ForwardIterator<T, IterImpl, iter::Const_tag>;
        using value_type = T;

    public:
        CompleteBinTree() noexcept = default;
        ~CompleteBinTree() noexcept = default;

        CompleteBinTree (Self&& rhs) noexcept
            : impl (std::move (rhs.impl))
            , height (std::exchange (rhs.height, 0))
        {}

        CompleteBinTree (Self const& rhs)
            : impl (rhs.impl)
            , height (rhs.height)
        {}

        template <class Iter, class = iter::EnableIfForward<Iter>>
        CompleteBinTree (Iter beg, Iter end) {
            algs::copy (beg, end, iter::add_iterator (*this));
        }

        CompleteBinTree (std::initializer_list<T> iList) {
            algs::copy (iList.begin(), iList.end(), iter::add_iterator (*this));
        }

        CompleteBinTree (std::size_t count, T const& value = T()) {
            while (count--) {
                add (value);
            }
        }

        CompleteBinTree& operator= (CompleteBinTree&& rhs) noexcept {
            if (this != &rhs) {
                auto tmp = std::move (rhs);
                swap (tmp);
            } 
            return *this;
        }

        CompleteBinTree& operator= (CompleteBinTree const& rhs) {
            if (this != &rhs) {
                auto tmp = rhs;
                swap (tmp);
            }
            return *this;
        }

        bool empty() const noexcept {
            return impl.empty();
        }

        std::size_t size() const noexcept {
            return not empty()
                 ? impl.root()->kids + 1
                 : 0;
        }

        void swap (CompleteBinTree& rhs) noexcept {
            std::swap (impl, rhs.impl);
            std::swap (height, rhs.height);
        }

        auto begin() const noexcept {
            return empty()
                 ? ConstIterator{}
                 : ConstIterator (impl.root());
        }

        auto end() const noexcept {
            return ConstIterator{};
        }
   
        template <typename... Ts>
        void emplace_add (Ts&&... params) {
            impl.emplace (
                Tilt::to_left
              , insert_position()
              , std::forward<Ts> (params)...
            );
        }

        void add (T&& value) {
            emplace_add (std::move (value));
        }

        void add (T const& value) {
            emplace_add (value);
        }

        void pop() noexcept {
            impl.erase_leaf (delete_position());
        }

    private:
        bool is_complete (BranchIt it, std::size_t h) const noexcept {
            return it.is_end()
                or std::pow (2, h) - 2 == it->kids; 
        }

        BranchIt insert_position () noexcept {
            auto it = impl.root();

            if (is_complete (it, height)) {
                ++height;
            }

            for (auto h = height - 1; h > 0; --h) {
                ++it->kids;

                if (it.left().is_end())
                    return it.left();

                if (is_complete (it.left(), h)) {
                    it.to_right();
                } else {
                    it.to_left();
                }
            }

            return it;
        }

        BranchIt delete_position() noexcept {
            auto it = impl.root();

            for (auto h = height - 1; h > 0; --h) {
                --it->kids;

                if (is_complete (it.right(), h-1)) {
                    it.to_left();
                } else {
                    it.to_right();
                }
            }

            if (is_complete (impl.root(), height - 1)) {
                --height;
            }

            return it;
        }

    private:       
        Impl impl{};
        std::size_t height = 0;
    };


    template <typename T>
    struct CompleteBinTree<T>::Node {
        template <typename... Args>
        Node (Args&&... args)
            : value (std::forward<Args> (args)...)
        {}

        T value;
        std::size_t kids = 0;
    };


    template <typename T>
    class CompleteBinTree<T>::IterImpl {
        friend CompleteBinTree;

    public:
        IterImpl() noexcept = default;

        IterImpl (BranchIt root) {
            queue.push_back (root);
        }
    
    protected:
        bool equal (IterImpl const& rhs) const noexcept {
            if (is_end() or rhs.is_end()){
                return is_end() == rhs.is_end();
            }

            return b_it() == rhs.b_it();
        }

        void next() noexcept {
            if (not b_it().left().is_end()) {
                queue.push_back (b_it().left());
                
                if (not b_it().right().is_end()) {
                    queue.push_back (b_it().right());
                }
            }
            queue.pop_front();
        }
            
        T& get_value() const noexcept {
            return const_cast<T&> (b_it()->value);
        }
    private:
        auto& b_it() const noexcept {
            return queue.front();
        }

        bool is_end() const noexcept {
            return queue.empty();
        }
    
    protected:
        Queue<BranchIt> queue{};
    };

}

#endif