// CSC Latin America 2026 - Particle Benchmarks
#include <benchmark/benchmark.h>
#include "Particle.hpp"

using namespace csc2026;

static void BM_ParticleConstruction(benchmark::State& state) {
    for (auto _ : state) {
        Particle p(1.0, 2.0, 3.0, 0.139);
        benchmark::DoNotOptimize(p);
    }
}
BENCHMARK(BM_ParticleConstruction);

static void BM_ParticlePt(benchmark::State& state) {
    Particle p(10.0, 20.0, 30.0, 0.139);
    for (auto _ : state) {
        double pt = p.pt();
        benchmark::DoNotOptimize(pt);
    }
}
BENCHMARK(BM_ParticlePt);

static void BM_ParticleEnergy(benchmark::State& state) {
    Particle p(10.0, 20.0, 30.0, 0.139);
    for (auto _ : state) {
        double e = p.energy();
        benchmark::DoNotOptimize(e);
    }
}
BENCHMARK(BM_ParticleEnergy);

static void BM_ParticleAddition(benchmark::State& state) {
    Particle p1(10.0, 20.0, 30.0, 0.139);
    Particle p2(-5.0, 15.0, -10.0, 0.139);
    for (auto _ : state) {
        Particle sum = p1 + p2;
        benchmark::DoNotOptimize(sum);
    }
}
BENCHMARK(BM_ParticleAddition);

static void BM_InvariantMass(benchmark::State& state) {
    Particle p1(45.0, 0.0, 45.0, 0.000511);
    Particle p2(-45.0, 0.0, -45.0, 0.000511);
    for (auto _ : state) {
        double m = invariantMass(p1, p2);
        benchmark::DoNotOptimize(m);
    }
}
BENCHMARK(BM_InvariantMass);

// Benchmark with varying number of particles
static void BM_PtCalculationBatch(benchmark::State& state) {
    const int n = state.range(0);
    std::vector<Particle> particles;
    particles.reserve(n);
    for (int i = 0; i < n; ++i) {
        particles.emplace_back(i * 0.1, i * 0.2, i * 0.3, 0.139);
    }
    
    for (auto _ : state) {
        double sum = 0.0;
        for (const auto& p : particles) {
            sum += p.pt();
        }
        benchmark::DoNotOptimize(sum);
    }
    state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_PtCalculationBatch)->Range(64, 4096);

BENCHMARK_MAIN();
