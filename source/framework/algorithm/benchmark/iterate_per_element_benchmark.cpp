#include "lue/framework/core/component/partitioned_array.hpp"
#include "lue/framework/algorithm/copy.hpp"
#include "lue/framework/algorithm/fill.hpp"
#include "lue/framework/algorithm/iterate_per_element.hpp"
#include "lue/framework/algorithm/uniform.hpp"
#include "lue/framework/benchmark/benchmark.hpp"
#include "lue/framework/benchmark/hpx_main.hpp"
#include <hpx/include/iostreams.hpp>
// #include <hpx/include/parallel_execution.hpp>


namespace lue {
namespace benchmark {
namespace detail {

template<
    typename Element,
    std::size_t rank>
void iterate_per_element(
    Task const& task,
    std::size_t const max_tree_depth)
{
    assert(max_tree_depth > 0);

    using Array = PartitionedArray<Element, rank>;
    using Shape = typename Array::Shape;

    Shape shape;
    std::copy(
        task.array_shape().begin(), task.array_shape().end(),
        shape.begin());

    Shape partition_shape;
    std::copy(
        task.partition_shape().begin(), task.partition_shape().end(),
        partition_shape.begin());

    // → Create initial array
    Array state{shape, partition_shape};
    hpx::cout << describe(state) << hpx::endl;

    assert(state.shape() == shape);

    // Fill array with random numbers
    // hpx::shared_future<Element> min_nr_iterations =
    //     hpx::make_ready_future<Element>(20);
    hpx::shared_future<Element> max_nr_iterations =
        hpx::make_ready_future<Element>(50);

    // uniform(min_nr_iterations, max_nr_iterations, state).wait();

    fill(state, max_nr_iterations).wait();

    hpx::lcos::local::sliding_semaphore semaphore{
        static_cast<std::int64_t>(max_tree_depth)};

    for(std::size_t i = 0; i < task.nr_time_steps(); ++i) {

        // Wait if there are more than max_tree_depth iterations in flight
        semaphore.wait(i);

        state = iterate_per_element(state);

        hpx::cout << '.' << hpx::flush;

        // Attach a continuation to the state at the current time
        // step. Once it is finished, signal the semaphore so it knowns
        // that we can have another iteration in flight.
        hpx::when_all_n(state.begin(), state.nr_partitions()).then(
            hpx::launch::sync,
            [&semaphore, i](
                auto const&)
            {
                semaphore.signal(i);
            });
    }

    hpx::cout << "!" << hpx::flush;

    hpx::wait_all_n(state.begin(), state.nr_partitions());

    hpx::cout << hpx::endl;
}

}  // namespace detail


void iterate_per_element(
    Task const& task,
    std::size_t const max_tree_depth)
{
    // hpx::parallel::execution::default_executor high_priority_executor{
    //     hpx::threads::thread_priority_high};

    using Element = std::int32_t;

    switch(task.rank()) {
        case 2: {
            // hpx::async(
            //     high_priority_executor,
            //     &detail::iterate_per_element<Element, 2>,
            //     task, max_tree_depth).wait();
            detail::iterate_per_element<Element, 2>(task, max_tree_depth);
            break;
        }
    }
}

}  // namespace benchmark
}  // namespace lue


auto setup_benchmark(
        int /* argc */,
        char* /* argv */[],
        lue::benchmark::Environment const& environment,
        lue::benchmark::Task const& task)
{
    // This function is called on the main locality. Return a callable that
    // performs the work to benchmark.

    // Function to benchmark
    auto callable = [](
        lue::benchmark::Environment const& environment,
        lue::benchmark::Task const& task)
    {
        std::size_t const max_tree_depth = environment.max_tree_depth()
            ? *environment.max_tree_depth()
            : task.nr_time_steps();

        lue::benchmark::iterate_per_element(task, max_tree_depth);
    };

    return lue::benchmark::Benchmark{std::move(callable), environment, task};
}


LUE_CONFIGURE_HPX_BENCHMARK()
