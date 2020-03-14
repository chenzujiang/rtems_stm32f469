#include <rtems.h>
#include <libchip/serial.h>
#include <libchip/sersupp.h>

bool libchip_serial_default_probe(int minor)
{
  /*如果配置依赖探测有本地设备，然后假定他在这里
   * If the configuration dependent probe has located the device then
   * assume it is there
   */

  return true;
}
