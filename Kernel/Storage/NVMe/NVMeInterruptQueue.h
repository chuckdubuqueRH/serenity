/*
 * Copyright (c) 2022, Pankaj R <pankydev8@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Kernel/Interrupts/PCIIRQHandler.h>
#include <Kernel/Storage/NVMe/NVMeQueue.h>

namespace Kernel {

class NVMeInterruptQueue : public NVMeQueue
    , public PCIIRQHandler {
public:
    NVMeInterruptQueue(PCI::Device& device, NonnullOwnPtr<Memory::Region> rw_dma_region, Memory::PhysicalPage const& rw_dma_page, u16 qid, u8 irq, u32 q_depth, OwnPtr<Memory::Region> cq_dma_region, Vector<NonnullRefPtr<Memory::PhysicalPage>> cq_dma_page, OwnPtr<Memory::Region> sq_dma_region, Vector<NonnullRefPtr<Memory::PhysicalPage>> sq_dma_page, Memory::TypedMapping<DoorbellRegister volatile> db_regs);
    void submit_sqe(NVMeSubmission& submission) override;
    virtual ~NVMeInterruptQueue() override {};
    virtual StringView purpose() const override { return "NVMe"sv; };

private:
    virtual void complete_current_request(u16 cmdid, u16 status) override;
    bool handle_irq(RegisterState const&) override;
};
}
