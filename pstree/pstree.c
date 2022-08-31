#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

typedef struct
{
  int pid;
  int ppid;
  int used;
} pid_ppid_node;

typedef struct
{
  int nodelen;
  pid_ppid_node *nodelist;
} pid_ppid_list;

void print_usage(void);
void dfs_build_tree(pid_ppid_list p_pp_list, int index, int father);

// 打印 pid 树，递归思想
void dfs_build_tree(pid_ppid_list p_pp_list, int index, int father)
{
  if (index == 0)
  {
    printf("0─┬─\n");
  }
  if (p_pp_list.nodelen <= 0)
  {
    printf("pid_ppid_list nodelen errror , it`s too min,print tree error ! ! !");
    return;
  }
  if (index == p_pp_list.nodelen)
  {
    return;
  }

  for (int i = 0; i < p_pp_list.nodelen; i++)
  {
    if (p_pp_list.nodelist[i].ppid == father && p_pp_list.nodelist[i].used == 0)
    {
      printf(" ├");
      for (int j = 0; j < index - 1; j++)
      {
        printf("    ");
      }
      if (index == 1)
      {
        printf("────");
      }
      else
      {
        printf("└───");
      }

      printf("%d\n", p_pp_list.nodelist[i].pid);
      p_pp_list.nodelist[i].used = 1;
      dfs_build_tree(p_pp_list, index + 1, p_pp_list.nodelist[i].pid);
      p_pp_list.nodelist[i].used = 0;
    }
  }
  return;
}

/*
  pid 和 ppid 获取并构建 pid_ppid_list
*/
pid_ppid_node get_pid_ppid(char filepath[])
{
  FILE *fp = NULL;
  fp = fopen(filepath, "r");
  char line[1024] = {0};
  pid_ppid_node node;
  // exit(0);
  int count = 0;
  if (!fp)
  {
    return node;
  }
  while (1)
  {
    if (EOF == fscanf(fp, "%s", line))
    {
      break;
    }
    if (strcmp(line, "Pid:") == 0)
    {
      count = count + 1;
      fscanf(fp, "%s", line); // pid_no
      node.pid = atoi(line);
      fscanf(fp, "%s", line); // ppid
      fscanf(fp, "%s", line); // ppid_no
      node.ppid = atoi(line);
    }
  }
  fclose(fp);
  return node;
};
/*
  根据 /proc 目录内容 寻找 相关进程信息
*/
pid_ppid_list traverse_dir(char *argv[])
{
  DIR *dp;
  struct dirent *filename;
  pid_ppid_list p_pp_list;
  pid_ppid_node id_list[1024 * 10];
  int index = 0;
  dp = opendir("/proc");
  if (!dp)
  {
    fprintf(stderr, "open directory error\n");
    return p_pp_list;
  }
  while ((filename = readdir(dp)))
  {
    if (1 && (filename->d_name[0] >= '0' && filename->d_name[0] <= '9'))
    {
      char filepath[500] = "/proc/";
      strcat(filepath, filename->d_name);
      strcat(filepath, "/status");
      id_list[index] = get_pid_ppid(filepath);
      index += 1;
    }
  }
  closedir(dp);
  p_pp_list.nodelen = index;
  p_pp_list.nodelist = id_list;
  return p_pp_list;
};

int main(int argc, char *argv[])
{
  pid_ppid_list p_pp_list;

  if (argc < 2 || strcmp(argv[1], "-V") == 0)
  {
    printf("Author: Build By XuXin \n"
           "Version: 1.0 \n"
           "Arguments: 1. -p  (--show-pid) build pstree order by pid\n"
           "           2. -V version\n");
    exit(0);
  }
  if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-P") == 0)
  {
    p_pp_list = traverse_dir(argv);
    dfs_build_tree(p_pp_list, 0, 0);
  }

  return 0;
}
