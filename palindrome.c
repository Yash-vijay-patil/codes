#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node*next;
};
void rev(struct node**head);
void addE(struct node**head,int e);
void display(struct node*head);
int com(struct node*fH,struct node*sH);
int pal(struct node*head);
int  main()
{
  struct node*head=NULL;
  int n;
  printf("Enter no. of elements to be in list\n");
  scanf("%d",&n);
  int i,e;
  for(i=0;i<n;i++)
  {
      scanf("%d",&e);
      addE(&head,e);
  }
  display(head);
  int v=pal(head);
  if(v==1)
  {
      printf("The given list is palindrome\n");
      display(head);
  }
  else
  {
      printf("The given list is not  palindrome\n");
  }


}
void display(struct node*head)
{
    struct node*cur=head;
    while(cur)
    {
        printf("%d\t",cur->data);
        cur=cur->next;
    }
}
void addE(struct node**head,int e)
{
    struct node*p,*cur;
    p=(struct node*)malloc(sizeof(struct node));
    if(p==NULL)
    {
        perror("Memory full\n");
        return;
    }
    p->data=e;
    p->next=NULL;
    if(*head==NULL)
        *head=p;
    else
    {
        cur=*head;
        while(cur->next)
        {
            cur=cur->next;
    }
    cur->next=p;

    }
}
int pal(struct node*head)
{
    if(head==NULL)
        return 1;
    struct node *s=head;
    struct node*f=head;
    struct node*p=NULL;

    while(f&&f->next)
    {
        f=f->next->next;
        p=s;
        s=s->next;
    }
    struct node*fH=head;
    struct node*sH;
    if(f!=NULL)
        sH=s->next;
    else
        sH=s;
    p->next=NULL;
    if(f!=NULL)
        s->next=NULL;
    rev(&sH);
    int c=com(fH,sH);
    rev(&sH);
    p->next=s;
    if(f!=NULL)
        s->next=sH;
    return c;
}
int com(struct node*fH,struct node*sH)
{
    while(fH&&sH)
    {
        if(fH->data!=sH->data)
            return 0;

        fH=fH->next;
        sH=sH->next;
        if(fH==NULL&&sH==NULL)
            return 1;
        else
            return 0;
    }
}
void rev(struct node**head)
{
    struct node*p,*r;
    struct node*q=NULL;
    p=*head;
    if(p!=NULL)
        q=p->next;
    while(q!=NULL)
    {
        q->next=p;
        p=q;
        q=r;
        if(r!=NULL)
            r=r->next;
    }
    if(*head!=NULL)
        (*head)->next=NULL;
    *head=p;
}
