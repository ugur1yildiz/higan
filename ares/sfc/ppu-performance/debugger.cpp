auto PPU::Debugger::load(Node::Object parent, Node::Object from) -> void {
  memory.vram = Node::append<Node::Memory>(parent, from, "PPU VRAM");
  memory.vram->setSize(ppu.vram.mask + 1 << 1);
  memory.vram->setRead([&](uint32 address) -> uint8 {
    return ppu.vram.data[address >> 1 & ppu.vram.mask].byte(address & 1);
  });
  memory.vram->setWrite([&](uint32 address, uint8 data) -> void {
    ppu.vram.data[address >> 1 & ppu.vram.mask].byte(address & 1) = data;
  });

  memory.oam = Node::append<Node::Memory>(parent, from, "PPU OAM");
  memory.oam->setSize(512 + 32);
  memory.oam->setRead([&](uint32 address) -> uint8 {
    return ppu.obj.oam.read(address);
  });
  memory.oam->setWrite([&](uint32 address, uint8 data) -> void {
    return ppu.obj.oam.write(address, data);
  });

  memory.cgram = Node::append<Node::Memory>(parent, from, "PPU CGRAM");
  memory.cgram->setSize(256 << 1);
  memory.cgram->setRead([&](uint32 address) -> uint8 {
    return ppu.dac.cgram[address >> 1 & 255].byte(address & 1);
  });
  memory.cgram->setWrite([&](uint32 address, uint8 data) -> void {
    ppu.dac.cgram[address >> 1 & 255].byte(address & 1) = data;
  });
}
