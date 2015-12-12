package GUI;

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class CDateUtils
{
  public static final String DATE_FORMAT_NOW = "dd-MM-yyyy HH:mm:ss";

  public static String now()
  {
    Calendar cal = Calendar.getInstance();
    SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
    return sdf.format(cal.getTime());
  }
}